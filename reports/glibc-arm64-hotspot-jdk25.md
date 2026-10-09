---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:28:09 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791530651 48
1791530656 48
1791530661 48
1791530666 48
1791530671 48
1791530676 48
1791530681 48
1791530686 48
1791530691 48
1791530696 48
1791530701 48
1791530706 48
1791530711 48
1791530716 48
1791530722 48
1791530727 48
1791530732 48
1791530737 48
1791530742 48
1791530747 48
```
</details>

---

