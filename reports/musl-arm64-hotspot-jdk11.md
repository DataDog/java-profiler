---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:31:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1789719992 9
1789719997 9
1789720002 9
1789720007 9
1789720012 14
1789720017 14
1789720022 14
1789720027 14
1789720032 14
1789720037 14
1789720042 14
1789720047 14
1789720052 14
1789720057 14
1789720062 14
1789720067 14
1789720072 14
1789720077 14
1789720082 14
1789720087 14
```
</details>

---

