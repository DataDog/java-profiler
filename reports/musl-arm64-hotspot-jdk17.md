---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:07:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 12 |
| Allocations | 96 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1794394992 14
1794394997 14
1794395002 14
1794395007 14
1794395012 14
1794395017 14
1794395022 14
1794395027 14
1794395032 14
1794395037 14
1794395042 14
1794395047 14
1794395052 14
1794395057 34
1794395062 34
1794395067 34
1794395072 34
1794395077 34
1794395082 34
1794395087 32
```
</details>

---

