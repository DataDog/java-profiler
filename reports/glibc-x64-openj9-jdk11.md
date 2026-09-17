---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:03:56 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 995 |
| Sample Rate | 16.58/sec |
| Health Score | 1036% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1789682158 77
1789682163 77
1789682168 77
1789682173 77
1789682178 77
1789682183 77
1789682188 77
1789682193 77
1789682198 77
1789682203 77
1789682208 77
1789682213 77
1789682218 79
1789682223 79
1789682228 79
1789682233 79
1789682238 79
1789682243 79
1789682248 79
1789682253 79
```
</details>

---

