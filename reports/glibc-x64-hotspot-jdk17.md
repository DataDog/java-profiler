---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 07:20:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 68-79 cores)</summary>

```
1795436138 79
1795436143 79
1795436148 79
1795436153 79
1795436158 79
1795436163 79
1795436168 79
1795436173 79
1795436178 79
1795436183 79
1795436188 68
1795436193 68
1795436198 68
1795436203 68
1795436208 68
1795436213 68
1795436218 68
1795436223 68
1795436228 68
1795436233 68
```
</details>

---

