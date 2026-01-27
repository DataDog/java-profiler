---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 20.90/sec |
| Health Score | 1306% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1769514149 32
1769514154 32
1769514159 32
1769514164 32
1769514169 32
1769514174 32
1769514179 32
1769514184 32
1769514189 22
1769514194 22
1769514199 22
1769514204 22
1769514209 22
1769514214 22
1769514219 22
1769514224 22
1769514229 22
1769514234 22
1769514239 22
1769514244 22
```
</details>

---

