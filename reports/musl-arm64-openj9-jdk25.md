---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 08:24:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787055564 64
1787055569 64
1787055574 64
1787055579 64
1787055584 64
1787055589 64
1787055594 64
1787055599 64
1787055604 64
1787055609 64
1787055614 64
1787055619 64
1787055624 64
1787055629 64
1787055634 64
1787055639 64
1787055644 64
1787055649 64
1787055654 64
1787055659 64
```
</details>

---

