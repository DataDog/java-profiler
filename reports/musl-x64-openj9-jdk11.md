---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:30:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 11 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1792765524 68
1792765529 68
1792765534 64
1792765539 64
1792765544 64
1792765549 64
1792765554 66
1792765559 66
1792765564 66
1792765569 66
1792765574 66
1792765579 66
1792765584 66
1792765589 66
1792765594 66
1792765599 66
1792765604 66
1792765609 66
1792765614 66
1792765619 66
```
</details>

---

