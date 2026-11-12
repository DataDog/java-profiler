---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:35:19 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 76-88 cores)</summary>

```
1794508136 76
1794508141 76
1794508146 76
1794508151 82
1794508156 82
1794508161 82
1794508166 82
1794508171 82
1794508176 82
1794508181 82
1794508186 88
1794508191 88
1794508196 88
1794508201 88
1794508207 88
1794508212 88
1794508217 88
1794508222 88
1794508227 88
1794508232 88
```
</details>

---

