---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 07:05:25 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1795608061 25
1795608066 25
1795608071 25
1795608076 25
1795608081 25
1795608086 25
1795608091 25
1795608096 25
1795608101 25
1795608106 30
1795608111 30
1795608116 30
1795608121 30
1795608126 30
1795608131 30
1795608136 30
1795608141 30
1795608146 30
1795608151 30
1795608156 29
```
</details>

---

