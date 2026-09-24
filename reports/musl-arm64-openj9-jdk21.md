---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:28:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790241555 46
1790241560 46
1790241565 46
1790241570 46
1790241575 46
1790241580 48
1790241585 48
1790241591 48
1790241596 48
1790241601 48
1790241606 48
1790241611 48
1790241616 48
1790241621 48
1790241626 48
1790241631 48
1790241636 48
1790241641 48
1790241646 48
1790241651 48
```
</details>

---

