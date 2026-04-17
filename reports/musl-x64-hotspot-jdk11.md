---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-17 08:06:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (5 unique values: 59-69 cores)</summary>

```
1776427132 63
1776427137 63
1776427142 63
1776427147 63
1776427152 63
1776427157 63
1776427162 63
1776427167 63
1776427172 59
1776427177 59
1776427182 59
1776427187 64
1776427192 64
1776427197 64
1776427202 64
1776427207 69
1776427212 69
1776427217 69
1776427222 69
1776427227 69
```
</details>

---

