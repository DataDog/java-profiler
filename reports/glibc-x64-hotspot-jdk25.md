---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 00:06:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794978168 79
1794978173 79
1794978178 79
1794978183 79
1794978188 79
1794978193 79
1794978198 79
1794978203 79
1794978208 79
1794978213 81
1794978218 81
1794978223 81
1794978228 81
1794978233 81
1794978238 81
1794978243 81
1794978248 81
1794978253 81
1794978258 81
1794978263 81
```
</details>

---

