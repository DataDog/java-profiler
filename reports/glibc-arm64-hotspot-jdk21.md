---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 11:50:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 14 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793288722 48
1793288727 48
1793288732 48
1793288737 48
1793288742 48
1793288747 48
1793288752 48
1793288757 48
1793288762 48
1793288767 48
1793288772 48
1793288777 48
1793288782 48
1793288787 48
1793288792 48
1793288797 48
1793288802 48
1793288807 48
1793288812 48
1793288817 48
```
</details>

---

