---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:28:37 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1790094058 57
1790094063 57
1790094068 57
1790094073 57
1790094078 57
1790094083 57
1790094088 57
1790094093 57
1790094098 57
1790094103 57
1790094108 55
1790094113 55
1790094118 55
1790094123 55
1790094128 55
1790094133 55
1790094138 55
1790094143 55
1790094148 55
1790094153 57
```
</details>

---

