---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:44:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 11 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (3 unique values: 27-52 cores)</summary>

```
1792140009 27
1792140014 39
1792140019 39
1792140024 39
1792140029 39
1792140034 39
1792140039 39
1792140044 39
1792140049 39
1792140055 39
1792140060 39
1792140065 52
1792140070 52
1792140075 52
1792140080 52
1792140085 52
1792140090 52
1792140095 52
1792140100 52
1792140105 52
```
</details>

---

