---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:18:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1795641210 81
1795641215 81
1795641220 81
1795641225 81
1795641230 81
1795641235 81
1795641240 79
1795641245 79
1795641250 79
1795641255 79
1795641260 79
1795641265 79
1795641270 79
1795641275 79
1795641280 79
1795641285 79
1795641290 79
1795641295 79
1795641300 79
1795641305 79
```
</details>

---

