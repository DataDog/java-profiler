---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:29:30 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (4 unique values: 24-34 cores)</summary>

```
1795630939 34
1795630944 34
1795630949 34
1795630954 34
1795630959 34
1795630964 34
1795630969 32
1795630974 32
1795630979 32
1795630984 32
1795630989 32
1795630994 32
1795630999 32
1795631004 32
1795631009 34
1795631014 34
1795631019 29
1795631024 29
1795631029 29
1795631034 29
```
</details>

---

