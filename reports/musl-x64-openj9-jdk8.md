---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 37-46 cores)</summary>

```
1769697807 39
1769697812 39
1769697817 37
1769697822 37
1769697827 37
1769697832 37
1769697837 37
1769697842 37
1769697847 37
1769697852 42
1769697857 42
1769697862 42
1769697867 46
1769697872 46
1769697877 44
1769697882 44
1769697887 44
1769697892 44
1769697897 44
1769697902 44
```
</details>

---

