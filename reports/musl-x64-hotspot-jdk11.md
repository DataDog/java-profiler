---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 06:39:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 79-86 cores)</summary>

```
1794224114 79
1794224119 79
1794224124 79
1794224129 79
1794224134 79
1794224139 79
1794224144 79
1794224149 81
1794224154 81
1794224159 81
1794224164 81
1794224169 81
1794224174 81
1794224179 81
1794224184 81
1794224189 81
1794224194 81
1794224199 81
1794224204 81
1794224209 81
```
</details>

---

