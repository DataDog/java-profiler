---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:56:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 50-57 cores)</summary>

```
1795434723 55
1795434728 55
1795434733 55
1795434738 55
1795434743 55
1795434748 55
1795434753 57
1795434758 57
1795434763 57
1795434768 57
1795434773 55
1795434778 55
1795434783 55
1795434788 55
1795434793 55
1795434798 55
1795434803 55
1795434808 55
1795434813 55
1795434818 55
```
</details>

---

