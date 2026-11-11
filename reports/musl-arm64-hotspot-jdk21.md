---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 06:07:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (4 unique values: 14-34 cores)</summary>

```
1794394965 16
1794394970 16
1794394975 16
1794394980 16
1794394985 14
1794394990 14
1794394995 14
1794395000 14
1794395005 14
1794395010 14
1794395015 14
1794395020 14
1794395025 14
1794395030 14
1794395035 14
1794395040 14
1794395045 14
1794395050 14
1794395055 14
1794395060 34
```
</details>

---

