---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:43:38 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1794487195 96
1794487200 96
1794487205 96
1794487210 96
1794487215 96
1794487220 96
1794487225 96
1794487230 94
1794487235 94
1794487240 94
1794487245 94
1794487250 90
1794487255 90
1794487260 90
1794487265 90
1794487270 90
1794487275 90
1794487280 90
1794487285 90
1794487290 90
```
</details>

---

