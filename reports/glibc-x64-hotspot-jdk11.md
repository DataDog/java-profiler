---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 04:34:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787128133 32
1787128138 32
1787128143 32
1787128148 32
1787128153 32
1787128158 32
1787128163 32
1787128168 32
1787128173 32
1787128178 32
1787128183 32
1787128188 32
1787128193 32
1787128198 32
1787128203 32
1787128208 32
1787128213 32
1787128218 32
1787128223 32
1787128228 32
```
</details>

---

