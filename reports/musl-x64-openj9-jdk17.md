---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-21 10:43:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1162 |
| Sample Rate | 19.37/sec |
| Health Score | 1211% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 42-56 cores)</summary>

```
1776782161 42
1776782166 42
1776782171 42
1776782176 47
1776782181 47
1776782186 56
1776782191 56
1776782196 56
1776782201 56
1776782206 56
1776782211 56
1776782216 56
1776782221 56
1776782227 56
1776782232 56
1776782237 56
1776782242 56
1776782247 56
1776782252 56
1776782257 56
```
</details>

---

