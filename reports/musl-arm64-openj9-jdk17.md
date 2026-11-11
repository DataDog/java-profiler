---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:07:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 14-34 cores)</summary>

```
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
1794395065 34
1794395070 34
1794395075 34
```
</details>

---

