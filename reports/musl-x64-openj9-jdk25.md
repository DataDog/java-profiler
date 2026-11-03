---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 14:44:32 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 60-66 cores)</summary>

```
1793734692 60
1793734697 60
1793734702 60
1793734707 60
1793734712 60
1793734717 60
1793734722 60
1793734727 60
1793734732 60
1793734737 60
1793734742 60
1793734747 60
1793734752 60
1793734757 60
1793734762 60
1793734767 60
1793734772 60
1793734777 62
1793734783 62
1793734788 62
```
</details>

---

