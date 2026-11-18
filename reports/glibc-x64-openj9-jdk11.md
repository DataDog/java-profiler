---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:59:04 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (7 unique values: 57-69 cores)</summary>

```
1794999187 57
1794999192 57
1794999197 57
1794999202 64
1794999207 64
1794999212 64
1794999217 64
1794999222 64
1794999227 64
1794999232 62
1794999237 62
1794999242 62
1794999247 62
1794999252 62
1794999257 64
1794999262 64
1794999267 66
1794999272 66
1794999277 67
1794999282 67
```
</details>

---

