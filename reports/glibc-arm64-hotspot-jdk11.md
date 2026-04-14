---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-14 18:05:36 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 11 |
| Allocations | 193 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776204100 64
1776204105 64
1776204110 64
1776204115 64
1776204120 64
1776204125 64
1776204130 64
1776204135 64
1776204140 64
1776204145 64
1776204150 64
1776204155 64
1776204160 64
1776204165 64
1776204170 64
1776204175 64
1776204180 64
1776204185 64
1776204190 64
1776204195 64
```
</details>

---

