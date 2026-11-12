---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:37:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
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
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794508166 92
1794508171 92
1794508176 92
1794508181 92
1794508186 92
1794508191 92
1794508196 92
1794508201 94
1794508206 94
1794508211 94
1794508216 94
1794508221 94
1794508226 94
1794508231 94
1794508236 94
1794508241 94
1794508246 94
1794508251 94
1794508256 94
1794508261 94
```
</details>

---

