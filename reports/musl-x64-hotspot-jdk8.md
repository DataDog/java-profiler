---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-28 12:04:40 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 71-77 cores)</summary>

```
1793203136 71
1793203141 71
1793203146 71
1793203151 71
1793203156 71
1793203161 71
1793203166 71
1793203171 71
1793203176 71
1793203181 71
1793203186 71
1793203191 71
1793203196 71
1793203201 71
1793203206 77
1793203211 77
1793203216 74
1793203221 74
1793203226 74
1793203231 74
```
</details>

---

