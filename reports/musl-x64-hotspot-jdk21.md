---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-21 14:31:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 14.55/sec |
| Health Score | 909% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 85-89 cores)</summary>

```
1776795946 85
1776795951 85
1776795956 85
1776795961 85
1776795966 85
1776795971 89
1776795976 89
1776795981 89
1776795986 89
1776795991 89
1776795996 89
1776796001 89
1776796006 89
1776796011 89
1776796016 89
1776796021 89
1776796026 89
1776796031 89
1776796036 89
1776796041 89
```
</details>

---

