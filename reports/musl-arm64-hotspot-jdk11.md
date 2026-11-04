---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 13:32:33 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793816883 30
1793816888 30
1793816893 30
1793816898 30
1793816903 30
1793816908 30
1793816913 30
1793816918 30
1793816923 30
1793816928 30
1793816933 30
1793816938 30
1793816943 30
1793816948 30
1793816953 30
1793816958 30
1793816963 30
1793816968 30
1793816973 30
1793816978 30
```
</details>

---

