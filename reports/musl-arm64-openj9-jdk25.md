---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:28:59 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 10 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790241559 46
1790241564 46
1790241569 46
1790241574 46
1790241579 48
1790241584 48
1790241589 48
1790241594 48
1790241599 48
1790241604 48
1790241609 48
1790241614 48
1790241619 48
1790241624 48
1790241629 48
1790241634 48
1790241639 48
1790241644 48
1790241649 48
1790241654 48
```
</details>

---

