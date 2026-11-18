---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:36:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 41-54 cores)</summary>

```
1795001511 41
1795001516 41
1795001521 41
1795001526 41
1795001531 41
1795001536 41
1795001541 41
1795001546 41
1795001551 41
1795001556 41
1795001561 41
1795001566 41
1795001571 41
1795001576 41
1795001581 41
1795001586 41
1795001591 54
1795001596 54
1795001601 54
1795001606 47
```
</details>

---

