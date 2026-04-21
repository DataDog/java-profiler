---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-21 14:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776795835 64
1776795840 64
1776795845 64
1776795850 64
1776795855 64
1776795860 64
1776795865 64
1776795870 64
1776795876 64
1776795881 64
1776795886 64
1776795891 64
1776795896 64
1776795901 64
1776795906 64
1776795911 64
1776795916 64
1776795921 64
1776795926 64
1776795931 64
```
</details>

---

