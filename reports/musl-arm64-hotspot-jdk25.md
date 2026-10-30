---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 10:36:05 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793370667 48
1793370672 48
1793370677 48
1793370682 48
1793370687 48
1793370692 48
1793370697 48
1793370702 48
1793370707 48
1793370712 48
1793370717 48
1793370722 48
1793370727 48
1793370732 48
1793370737 48
1793370742 48
1793370747 48
1793370752 48
1793370757 48
1793370762 48
```
</details>

---

