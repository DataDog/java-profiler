---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:45:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1789980007 49
1789980012 49
1789980017 49
1789980022 49
1789980027 49
1789980032 49
1789980037 49
1789980042 49
1789980047 49
1789980052 49
1789980057 49
1789980062 49
1789980067 49
1789980072 49
1789980077 49
1789980082 49
1789980087 64
1789980092 64
1789980097 44
1789980102 44
```
</details>

---

