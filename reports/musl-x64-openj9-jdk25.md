---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-02 12:55:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 12 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 50-75 cores)</summary>

```
1770054595 75
1770054600 55
1770054605 55
1770054610 55
1770054615 55
1770054620 50
1770054625 50
1770054630 50
1770054635 50
1770054640 64
1770054645 64
1770054650 64
1770054655 64
1770054660 64
1770054665 69
1770054670 69
1770054675 69
1770054680 69
1770054686 69
1770054691 69
```
</details>

---

