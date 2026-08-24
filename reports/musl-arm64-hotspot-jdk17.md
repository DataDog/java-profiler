---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-24 13:07:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787590915 64
1787590920 64
1787590925 64
1787590930 64
1787590935 64
1787590940 64
1787590945 64
1787590950 64
1787590955 64
1787590960 64
1787590965 64
1787590970 64
1787590975 64
1787590980 64
1787590985 64
1787590990 64
1787590995 64
1787591000 64
1787591005 64
1787591010 64
```
</details>

---

