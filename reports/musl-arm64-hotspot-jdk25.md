---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:34:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
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
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1795011928 55
1795011933 55
1795011938 55
1795011943 55
1795011948 55
1795011953 60
1795011958 60
1795011963 60
1795011968 60
1795011973 60
1795011978 60
1795011983 60
1795011988 60
1795011993 60
1795011998 60
1795012003 60
1795012008 60
1795012014 60
1795012019 60
1795012024 60
```
</details>

---

