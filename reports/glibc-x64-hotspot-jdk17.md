---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:34:54 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (4 unique values: 53-78 cores)</summary>

```
1790242184 53
1790242189 53
1790242194 61
1790242199 61
1790242204 61
1790242209 61
1790242214 61
1790242219 61
1790242224 61
1790242229 61
1790242234 61
1790242239 61
1790242244 61
1790242249 62
1790242254 62
1790242259 62
1790242264 62
1790242269 62
1790242274 62
1790242279 62
```
</details>

---

