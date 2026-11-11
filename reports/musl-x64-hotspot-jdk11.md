---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:26:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (6 unique values: 83-90 cores)</summary>

```
1794406993 84
1794406998 86
1794407003 86
1794407008 88
1794407013 88
1794407018 88
1794407023 90
1794407028 90
1794407033 85
1794407038 85
1794407043 85
1794407048 85
1794407053 85
1794407058 85
1794407063 83
1794407068 83
1794407073 83
1794407078 83
1794407083 83
1794407088 83
```
</details>

---

