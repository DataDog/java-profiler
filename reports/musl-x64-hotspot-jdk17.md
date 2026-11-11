---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:07:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 75-96 cores)</summary>

```
1794394992 92
1794394997 92
1794395002 92
1794395007 94
1794395012 94
1794395017 94
1794395022 94
1794395027 94
1794395032 94
1794395037 94
1794395042 94
1794395047 94
1794395052 94
1794395057 96
1794395062 96
1794395068 96
1794395073 96
1794395078 96
1794395083 96
1794395088 96
```
</details>

---

