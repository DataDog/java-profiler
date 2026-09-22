---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 13:14:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1790097001 41
1790097006 41
1790097011 41
1790097016 36
1790097021 36
1790097026 36
1790097031 36
1790097036 36
1790097041 36
1790097046 36
1790097051 36
1790097056 36
1790097061 36
1790097066 41
1790097071 41
1790097076 41
1790097081 41
1790097086 41
1790097091 41
1790097096 41
```
</details>

---

