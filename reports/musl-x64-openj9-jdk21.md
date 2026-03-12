---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-12 10:34:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 10 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 12 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 20-25 cores)</summary>

```
1773325702 20
1773325707 20
1773325712 20
1773325717 20
1773325722 20
1773325727 20
1773325732 20
1773325737 20
1773325742 20
1773325747 25
1773325752 25
1773325757 25
1773325762 25
1773325767 25
1773325772 25
1773325777 25
1773325782 25
1773325787 25
1773325792 25
1773325797 25
```
</details>

---

