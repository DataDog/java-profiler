---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 08:08:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 35-48 cores)</summary>

```
1789992230 40
1789992235 40
1789992240 40
1789992245 40
1789992250 40
1789992255 40
1789992260 40
1789992265 40
1789992270 40
1789992275 40
1789992280 40
1789992285 40
1789992290 40
1789992295 40
1789992300 35
1789992305 35
1789992310 43
1789992315 43
1789992320 43
1789992325 43
```
</details>

---

