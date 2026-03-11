---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-03-11 14:07:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 35-44 cores)</summary>

```
1773252111 40
1773252116 40
1773252121 40
1773252126 40
1773252131 40
1773252136 40
1773252141 40
1773252146 40
1773252151 40
1773252156 35
1773252161 35
1773252166 35
1773252171 35
1773252176 35
1773252181 39
1773252186 39
1773252191 44
1773252196 44
1773252201 44
1773252206 44
```
</details>

---

