---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:47:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794408164 48
1794408169 48
1794408174 46
1794408179 46
1794408184 46
1794408189 46
1794408194 46
1794408199 46
1794408204 46
1794408209 46
1794408214 46
1794408219 46
1794408224 46
1794408229 46
1794408234 48
1794408239 48
1794408244 48
1794408249 48
1794408254 48
1794408259 48
```
</details>

---

