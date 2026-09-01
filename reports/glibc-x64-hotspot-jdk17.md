---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-01 15:37:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 46-54 cores)</summary>

```
1788291141 52
1788291146 52
1788291151 52
1788291156 52
1788291161 52
1788291166 52
1788291171 54
1788291176 54
1788291181 54
1788291186 54
1788291191 54
1788291196 54
1788291201 46
1788291206 46
1788291211 46
1788291216 46
1788291221 46
1788291226 46
1788291231 46
1788291236 46
```
</details>

---

