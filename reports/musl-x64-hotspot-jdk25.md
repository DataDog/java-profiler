---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-16 11:32:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 15.40/sec |
| Health Score | 962% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 50-55 cores)</summary>

```
1776352986 55
1776352991 55
1776352996 55
1776353001 55
1776353006 55
1776353011 55
1776353016 50
1776353021 50
1776353026 50
1776353031 50
1776353036 50
1776353041 50
1776353046 50
1776353051 50
1776353056 50
1776353061 50
1776353066 50
1776353071 50
1776353076 50
1776353081 50
```
</details>

---

