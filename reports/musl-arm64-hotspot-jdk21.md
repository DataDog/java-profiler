---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:50:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 13-21 cores)</summary>

```
1794933907 13
1794933912 13
1794933917 13
1794933923 13
1794933928 13
1794933933 13
1794933938 13
1794933943 13
1794933948 13
1794933953 13
1794933958 13
1794933963 13
1794933968 13
1794933973 21
1794933978 21
1794933983 21
1794933988 21
1794933993 21
1794933998 21
1794934003 21
```
</details>

---

