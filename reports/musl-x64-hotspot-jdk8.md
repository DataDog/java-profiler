---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-26 09:45:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 80-96 cores)</summary>

```
1787751592 80
1787751597 80
1787751602 80
1787751607 80
1787751612 80
1787751617 80
1787751622 80
1787751627 80
1787751632 80
1787751637 80
1787751642 80
1787751647 80
1787751652 80
1787751657 80
1787751662 80
1787751667 80
1787751672 80
1787751677 80
1787751682 80
1787751687 96
```
</details>

---

