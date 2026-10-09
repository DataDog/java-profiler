---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-09 01:05:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1791522022 73
1791522027 73
1791522032 73
1791522037 73
1791522042 73
1791522047 73
1791522052 81
1791522057 81
1791522062 81
1791522067 81
1791522072 81
1791522077 81
1791522082 81
1791522087 81
1791522092 81
1791522097 81
1791522102 81
1791522107 81
1791522112 81
1791522117 81
```
</details>

---

