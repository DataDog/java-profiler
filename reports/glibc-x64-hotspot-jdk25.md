---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 16:56:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 81-96 cores)</summary>

```
1792702114 94
1792702119 94
1792702124 94
1792702129 94
1792702134 94
1792702139 94
1792702144 94
1792702149 94
1792702154 94
1792702159 96
1792702164 96
1792702169 84
1792702174 84
1792702179 84
1792702184 84
1792702189 84
1792702194 84
1792702199 84
1792702204 84
1792702209 84
```
</details>

---

