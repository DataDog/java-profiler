---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 03:32:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1794990494 31
1794990499 31
1794990504 31
1794990509 31
1794990514 31
1794990519 31
1794990524 31
1794990529 31
1794990534 31
1794990539 31
1794990544 31
1794990549 31
1794990554 33
1794990559 33
1794990564 33
1794990569 33
1794990574 33
1794990579 33
1794990584 33
1794990589 33
```
</details>

---

