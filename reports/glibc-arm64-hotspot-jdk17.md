---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 10:05:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776693517 64
1776693522 64
1776693527 64
1776693532 64
1776693537 64
1776693542 64
1776693547 64
1776693552 64
1776693557 64
1776693562 64
1776693567 64
1776693572 64
1776693577 64
1776693582 64
1776693587 64
1776693592 64
1776693597 64
1776693602 64
1776693607 64
1776693612 59
```
</details>

---

