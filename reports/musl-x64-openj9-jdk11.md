---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:22:28 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 49-54 cores)</summary>

```
1795429035 54
1795429040 54
1795429045 54
1795429050 50
1795429055 50
1795429060 50
1795429065 50
1795429070 50
1795429075 50
1795429080 54
1795429085 54
1795429090 54
1795429095 54
1795429100 54
1795429105 52
1795429110 52
1795429115 52
1795429120 52
1795429125 52
1795429130 52
```
</details>

---

