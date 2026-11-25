---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:30:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1795631110 30
1795631115 30
1795631120 30
1795631125 30
1795631130 30
1795631135 30
1795631140 30
1795631145 30
1795631150 30
1795631155 30
1795631160 26
1795631165 26
1795631170 26
1795631175 26
1795631180 26
1795631185 26
1795631190 26
1795631195 26
1795631200 26
1795631205 26
```
</details>

---

